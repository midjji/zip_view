# Build configuration
macro(BuildConfig)

    # Change the default build type from Debug to Release

    # The CACHE STRING logic here and elsewhere is needed to force CMake
    # to pay attention to the value of these variables.(for override)
    if(NOT CMAKE_BUILD_TYPE)
        MESSAGE("-- No build type specified; defaulting to CMAKE_BUILD_TYPE=Release.")
        set(CMAKE_BUILD_TYPE Debug CACHE STRING
            "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."  FORCE)
    else()
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            MESSAGE("\n${line}")
            MESSAGE("\n-- Build type: Debug. Performance will be terrible!")
            MESSAGE("-- Add -DCMAKE_BUILD_TYPE=Release to the CMake command line to get an optimized build.")
            MESSAGE("-- Add -DCMAKE_BUILD_TYPE=RelWithDebInfo to the CMake command line to get an faster build with symbols(-g).")
            MESSAGE("\n${line}")
        endif()
    endif()



    #list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
    #add_definitions("-std=c++11")
endmacro()

macro(WarningConfig)

    set(warn "")
    option(WError "Warnings are errors" OFF)

    if(WError)
        list(APPEND warn "-Werror ")
    endif()


    if(CMAKE_COMPILER_IS_GNUCXX)  # GCC
        message("GCC")
        list(APPEND warn -Wall)
        list(APPEND warn -Wextra)
        list(APPEND warn -Wstrict-aliasing)
        list(APPEND warn -Wdouble-promotion)
        list(APPEND warn -Weffc++)
        list(APPEND warn -Wnull-dereference)
        list(APPEND warn -Wsequence-point)
        #list(APPEND warn -Wshadow)
        list(APPEND warn -Wunsafe-loop-optimizations)


        list(APPEND warn -Wcast-qual)

        list(APPEND warn -Wuseless-cast)
        list(APPEND warn -Waddress)
        list(APPEND warn -Waggressive-loop-optimizations)
        list(APPEND warn -Winline)
        #set(warn "${warn} -Wno-unknown-pragmas")
        #set(warn "${warn} -Wno-sign-compare")
        #set(warn "${warn} -Wno-unused-parameter")
        #set(warn "${warn} -Wunused-parameter")
        #set(warn "${warn} -Wno-missing-field-initializers")
        #set(warn "${warn} -Wno-unused")
        #set(warn "${warn} -Wno-unused-function")
        #set(warn "${warn} -Wno-unused-label")
        #set(warn "${warn} -Wno-unused-parameter")
        #set(warn "${warn} -Wno-unused-value")
        #set(warn "${warn} -Wno-unused-variable")
        #set(warn "${warn} -Wno-unused-but-set-parameter")
        #set(warn "${warn} -Wno-unused-but-set-variable")

        #set(warn "${warn} -Wno-variadic-macros" )
        #set(warn "${warn} -Wno-deprecated-declarations" )

        #set(warn "${warn} -Wformat=2 ")
        #set(warn "${warn} -Wnounreachable-code")
        #set(warn "${warn} -Wswitch-default ")
        #set(warn "${warn}     -Winline ")
        #not relevant...
        #set(warn "${warn} -Wshadow")
        #set(warn "${warn} ")


    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message("Clang!")
        list(APPEND warn -W)
        list(APPEND warn -Wall)
        list(APPEND warn -Wextra)
        list(APPEND warn -WCL4)
        list(APPEND warn -Wabstract-vbase-init)
        list(APPEND warn -Warc-maybe-repeated-use-of-weak)
        list(APPEND warn -Warc-repeated-use-of-weak)
        list(APPEND warn -Warray-bounds-pointer-arithmetic)
        list(APPEND warn -Wassign-enum)

        list(APPEND warn -Watomic-properties)
        list(APPEND warn -Wauto-import)
        list(APPEND warn -Wbad-function-cast)
        list(APPEND warn -Wbitfield-enum-conversion)
        list(APPEND warn -Wbitwise-op-parentheses)


        # specical ones!
        list(APPEND warn -Wcast-align)
        list(APPEND warn -Wcast-qual)



        list(APPEND warn -Wchar-subscripts)
        list(APPEND warn -Wcomma)
        list(APPEND warn -Wconditional-type-mismatch)
        list(APPEND warn -Wconditional-uninitialized)
        list(APPEND warn -Wconfig-macros)
        list(APPEND warn -Wconstant-conversion)
        list(APPEND warn -Wconsumed)
        list(APPEND warn -Wconversion)

        list(APPEND warn -Wcustom-atomic-properties)
        list(APPEND warn -Wdate-time)

        list(APPEND warn -Wdelete-non-virtual-dtor)
        list(APPEND warn -Wdeprecated)
        list(APPEND warn -Wdeprecated-dynamic-exception-spec)
        list(APPEND warn -Wdeprecated-implementations)

        list(APPEND warn -Wdirect-ivar-access)
        list(APPEND warn -Wdisabled-macro-expansion)
        #list(APPEND warn -Wdocumentation)
        list(APPEND warn -Wduplicate-enum)
        list(APPEND warn -Wduplicate-method-arg)
        list(APPEND warn -Wduplicate-method-match)
        list(APPEND warn -Weffc++)
        list(APPEND warn -Wembedded-directive)

        list(APPEND warn -Wempty-translation-unit)
        list(APPEND warn -Wexpansion-to-defined)

        list(APPEND warn -Wexperimental-isel)
        list(APPEND warn -Wexplicit-ownership-type)
        list(APPEND warn -Wextra-semi)


        list(APPEND warn -Wflexible-array-extensions)
        list(APPEND warn -Wfloat-conversion)
        #list(APPEND warn -Wfloat-equal)
        list(APPEND warn -Wfloat-overflow-conversion)
        list(APPEND warn -Wfloat-zero-conversion)

        list(APPEND warn -Wfor-loop-analysis)
        list(APPEND warn -Wformat-nonliteral)
        list(APPEND warn -Wformat-non-iso)
        list(APPEND warn -Wformat-pedantic)
        list(APPEND warn -Wfour-char-constants)
        option(Warn_on_globals "Warn on globals" OFF)
        if(Warn_on_globals)
            list(APPEND warn -Wglobal-constructors)
        endif()


        list(APPEND warn -Wgnu)

        list(APPEND warn -Wheader-guard)
        list(APPEND warn -Wheader-hygiene)
        list(APPEND warn -Widiomatic-parentheses)
        list(APPEND warn -Wignored-qualifiers)
        list(APPEND warn -Wimplicit-atomic-properties)
        list(APPEND warn -Wimplicit)
        list(APPEND warn -Wimplicit-fallthrough)

        list(APPEND warn -Wimplicit-function-declaration)


        list(APPEND warn -Wimplicit-retain-self)
        list(APPEND warn -Wimport-preprocessor-directive-pedantic)


        list(APPEND warn -Winconsistent-dllimport)
        list(APPEND warn -Winconsistent-missing-destructor-override)
        list(APPEND warn -Winfinite-recursion)
        list(APPEND warn -Winvalid-or-nonexistent-directory)
        list(APPEND warn -Wkeyword-macro)
        list(APPEND warn -Wlanguage-extension-token)

        list(APPEND warn -Wlogical-op-parentheses)
        list(APPEND warn -Wmain)
        list(APPEND warn -Wmethod-signatures)
        list(APPEND warn -Wmismatched-tags)
        list(APPEND warn -Wmissing-braces)
        list(APPEND warn -Wmissing-field-initializers)
        list(APPEND warn -Wmissing-method-return-type)
        list(APPEND warn -Wmissing-noreturn)

        list(APPEND warn -Wmissing-variable-declarations)

        list(APPEND warn -Wmost)
        list(APPEND warn -Wmove)
        list(APPEND warn -Wnewline-eof)
        list(APPEND warn -Wnon-gcc)
        list(APPEND warn -Wnon-virtual-dtor)
        list(APPEND warn -Wnonportable-system-include-path)
        list(APPEND warn -Wnull-pointer-arithmetic)
        list(APPEND warn -Wnullable-to-nonnull-conversion)
        list(APPEND warn -Wobjc-interface-ivars)
        list(APPEND warn -Wobjc-messaging-id)
        list(APPEND warn -Wobjc-missing-property-synthesis)

        list(APPEND warn -Wold-style-cast)
        list(APPEND warn -Wover-aligned)
        list(APPEND warn -Woverlength-strings)
        list(APPEND warn -Woverloaded-virtual)
        list(APPEND warn -Woverriding-method-mismatch)
        list(APPEND warn -Wpacked)
        list(APPEND warn -Wpadded)
        list(APPEND warn -Wparentheses)


        list(APPEND warn -Wpessimizing-move)
        list(APPEND warn -Wpointer-arith)

        list(APPEND warn -Wpragma-pack)
        list(APPEND warn -Wpragma-pack-suspicious-include)
        list(APPEND warn -Wprofile-instr-missing)

        list(APPEND warn -Wrange-loop-analysis)
        list(APPEND warn -Wredundant-move)
        list(APPEND warn -Wredundant-parens)
        list(APPEND warn -Wreorder)
        #list(APPEND warn -Wreserved-id-macro)
        list(APPEND warn -Wretained-language-linkage)
        list(APPEND warn -Wreserved-user-defined-literal)

        list(APPEND warn -Wselector)
        list(APPEND warn -Wself-assign)
        list(APPEND warn -Wself-move)
        list(APPEND warn -Wsemicolon-before-method-body)


        #list(APPEND warn -Wshadow-all)
        list(APPEND warn -Wshadow)
        list(APPEND warn -Wshadow-field)
        #list(APPEND warn -Wshadow-field-in-constructor)
        list(APPEND warn -Wshadow-uncaptured-local)
        list(APPEND warn -Wshadow-field-in-constructor-modified)



        list(APPEND warn -Wshift-sign-overflow)

        list(APPEND warn -Wshorten-64-to-32)
        list(APPEND warn -Wsign-compare)

        list(APPEND warn -Wno-sign-conversion)

        list(APPEND warn -Wsigned-enum-bitfield)
        list(APPEND warn -Wsometimes-uninitialized)
        list(APPEND warn -Wspir-compat)
        list(APPEND warn -Wstatic-in-inline)
        list(APPEND warn -Wstrict-prototypes)
        list(APPEND warn -Wstrict-selector-match)
        list(APPEND warn -Wstring-conversion)
        list(APPEND warn -Wsuper-class-method-mismatch)
        list(APPEND warn -Wswitch-enum)
        list(APPEND warn -Wtautological-compare)
        list(APPEND warn -Wtautological-constant-in-range-compare)
        list(APPEND warn -Wtautological-overlap-compare)

        list(APPEND warn -Wthread-safety)

        list(APPEND warn -Wthread-safety-negative)
        list(APPEND warn -Wthread-safety-verbose)
        list(APPEND warn -Wthread-safety-beta)

        list(APPEND warn -Wtrigraphs)
        list(APPEND warn -Wundeclared-selector)
        #list(APPEND warn -Wundef)
        list(APPEND warn -Wundefined-func-template)
        list(APPEND warn -Wundefined-inline)
        list(APPEND warn -Wundefined-internal-type)
        list(APPEND warn -Wundefined-reinterpret-cast)
        list(APPEND warn -Wuninitialized)
        list(APPEND warn -Wunknown-escape-sequence)
        list(APPEND warn -Wunknown-pragmas)
        list(APPEND warn -Wunknown-sanitizers)
        list(APPEND warn -Wunknown-warning-option)
        list(APPEND warn -Wunneeded-internal-declaration)
        list(APPEND warn -Wunneeded-member-function)
        list(APPEND warn -Wunreachable-code)
        list(APPEND warn -Wunreachable-code-aggressive)
        list(APPEND warn -Wunused)
        list(APPEND warn -Wunused-const-variable)
        list(APPEND warn -Wunused-exception-parameter)
        list(APPEND warn -Wunused-function)
        list(APPEND warn -Wunused-label)
        list(APPEND warn -Wunused-lambda-capture)
        list(APPEND warn -Wunused-local-typedef)
        list(APPEND warn -Wunused-macros)
        list(APPEND warn -Wunused-member-function)
        list(APPEND warn -Wunused-parameter)
        list(APPEND warn -Wunused-private-field)
        list(APPEND warn -Wunused-property-ivar)
        list(APPEND warn -Wunused-template)
        list(APPEND warn -Wunused-value)
        list(APPEND warn -Wused-but-marked-unused)
        list(APPEND warn -Wunused-variable)
        list(APPEND warn -Wvariadic-macros)
        list(APPEND warn -Wvector-conversion)
        list(APPEND warn -Wweak-template-vtables)
        list(APPEND warn -Wweak-vtables)
        list(APPEND warn -Wzero-as-null-pointer-constant)
        list(APPEND warn -Wzero-length-array)


        list(APPEND warn-Rremark-backend-plugin)
        list(APPEND warn-Rsanitize-address)

        list(APPEND warn -Rmodule-build)
        list(APPEND warn -Rpass)
        list(APPEND warn -Rpass-analysis)

        # cuda stuff!
        list(APPEND warn -Wcuda-compat)

        # check specific to program version
        list(APPEND warn -Wc++11-extensions)
        list(APPEND warn -Wc++17-compat-pedantic)
    endif()


    add_compile_options(${warn})
    #message("warn: ${warn}")

endmacro()


macro(OptimizationConfig)
    if(CMAKE_COMPILER_IS_GNUCXX)  # GCC
        message("GCC")

        set(CMAKE_CXX_FLAGS_DEBUG " -fsanitize=undefined -fno-omit-frame-pointer -pg -g  " CACHE STRING "Fixed" FORCE) # dynamic is for the improved asserts
        set(CMAKE_C_FLAGS_DEBUG "-fsanitize=undefined -fno-omit-frame-pointer -pg -g -rdynamic " CACHE STRING "Fixed" FORCE) # dynamic is for the improved asserts
        set(CMAKE_CXX_FLAGS_RELEASE "-fsanitize=undefined -march=native  -O3  -DNDEBUG" CACHE STRING "Fixed" FORCE)
        set(CMAKE_C_FLAGS_RELEASE "-fsanitize=undefined -march=native  -O3  -DNDEBUG" CACHE STRING "Fixed" FORCE)


    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message("Clang!")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
        set(CMAKE_CXX_FLAGS_DEBUG " -fsanitize=undefined -fno-omit-frame-pointer -pg -g -rdynamic " CACHE STRING "Fixed" FORCE) # dynamic is for the improved asserts
        set(CMAKE_C_FLAGS_DEBUG "-fsanitize=undefined -fno-omit-frame-pointer -pg -g -rdynamic " CACHE STRING "Fixed" FORCE) # dynamic is for the improved asserts
        set(CMAKE_CXX_FLAGS_RELEASE "-fsanitize=undefined -march=native  -O3  -DNDEBUG" CACHE STRING "Fixed" FORCE)
        set(CMAKE_C_FLAGS_RELEASE "-fsanitize=undefined -march=native  -O3  -DNDEBUG" CACHE STRING "Fixed" FORCE)

    endif()

    message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
    if(NOT CMAKE_COMPILER_IS_GNUCXX)
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            message("TODO: fix opt options on ${CMAKE_CXX_COMPILER_ID}")
            set(CMAKE_CXX_FLAGS_RELEASE " -O0")
        endif()
    endif()

endmacro()

macro(print_list name list)
    message("${name}")
    foreach(item IN LISTS ${list})
        message("     ${item}")
    endforeach()
endmacro()

macro(print_filenames name list)
    message("${name}")
    foreach(item IN LISTS ${list})
        get_filename_component(filename ${item} NAME)
        message("     ${filename}")
    endforeach()
endmacro()

macro(display_library name includes libs) # maybe add defines
    message("${name}")
    set(tab "    ")
    message("${tab}includes:")
    foreach(item IN LISTS ${includes})
        message("${tab}${tab}${item}")
    endforeach()
    message("${tab}libs:")
    foreach(item IN LISTS ${libs})
        message("${tab}${tab}${item}")
    endforeach()
    message("")
endmacro()


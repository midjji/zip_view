# zip_view
Basic c++17 zip iterator, 

ever wanted to do 

for(a,b,c : zip(as, bs, cs )) like in python? 

This single header makes it possible to do 

for(auto [index, a,b,c]: zip(as,bs, cs)){}
for any iterable container (has begin,end)

which is equivalent to
for(uint64_t index=0;index<min((as,bs,cs...).size());++index){
  auto& a= as[index];
  auto& b= bs[index];
  auto& c= cs[index];
}
for any number of containers


This is a zip view! meaning it wont copy and will let you change the returned references. (a,b,c)
the tuple must be unpacked and will have index, + container elements. 
the return tuple is of references! meaning you can change the zipped container values. 
not for use with std algorithm without specialization. 


// this is a low cost abstraction, ideally zero, but clang and gcc does not actually optimize these as well as the simpler loop. 


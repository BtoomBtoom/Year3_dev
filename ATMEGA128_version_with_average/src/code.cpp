/*
   This is code for average function that takes in a container of value measured, new updated value that needs 
   to be added to the container, and the maximum number that container acquires to get the average value.

   Written by "Year3".
*/
#define limit 5         //limit number of the container

template <typename type>                  //template function in order to apply to all kind of array type
type average(type* c, const type &value, int count)
{
   if (count != limit-1)
   {
      c[count] = value;
      ++count;
      type sum = 0;
      for (int i =0; i<=count; ++i)
      {
         sum += c[i];
      }
      return sum / count+1;
   }
   else
   {
      for(int i=0;i<=count-1;++i)
      {
         c[i] = c[i+1];
      }
      c[count] = value;
      type sum = 0;
      for (int i =0;i<=count;++i)
      {
         sum += c[i];
         // std::cout << sum << '\n';
      }
      return sum / count+1;
   }
}

// int main()
// {

//    for(auto i:temperature)
//    {
//       std::cout << i <<'\n';
//    }

//    std::cout << "end temperature" << '\n';

//    for (auto i : humidity)
//    {
//       std::cout << i << '\n';
//    }

//    std::cout << "end humidity" << '\n';

//    std::cout << average(temperature, temperature_val, temperature_count) << '\n';

//    std::cout << average(humidity, humidity_val, humidity_count) << '\n' << "after: " << '\n';

//    for (auto i : humidity)
//    {
//       std::cout << i << '\n';
//    }

//    return 0;
// }
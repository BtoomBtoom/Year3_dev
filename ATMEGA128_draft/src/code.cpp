// #include <list>
// #include <iostream>

// double humidity_val = 10000;
// size_t humidity_count = 4;
// double humidity[5] = {45.67, 56.78, 78.34, 78.45, 98.34};

// int temperature_val = 10000;
// size_t temperature_count = 4;
// int temperature[5] = {89, 98, 76, 99, 67};

#define limit 5

template <typename type>
type average(type* c, const type &value, int count)
{
   if (count != limit-1)
   {
      c[count] = value;
      ++count;
      type sum = 0;
      for (int i =0;i<=count;++i)
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
import { useState, useEffect } from "react";

const UseFetch = (url) => {
   console.log("useFetch start!!!")
   let [humidity, getHumidity] = useState([])
   const getSensors = async () => {
      const response = await fetch(url,{
      'method':'GET',
      headers: {
        'Content-Type':'application/json',
         }
      });
      const new_sensors = await response.json()
      console.log(new_sensors)
      getHumidity(new_sensors)
      // if(new_sensors)
      // {
      //    console.log("Fetch data successfull!!")
      // }
   };

   useEffect(() => {
      getSensors();
   }, [humidity]);

   return {humidity};
};

export default UseFetch;
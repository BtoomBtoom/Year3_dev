import { useState, useEffect, useCallback } from "react";


const UseFetchTest = (url) => 
{
   let [loading, setLoading] = useState(true);
   let [data, setData] = useState([]);

   //useCallback does the job that only when 'url' change then 'getData' is re-render
   const getData = useCallback( 
      async () => 
      {
         let raw_data = await fetch(url);
         let new_data = await raw_data.json();
         if(new_data){setLoading(false);}
         setData(new_data);
      }, [url]);

   //useEffect is run only the first time initial render, and when 'url' or 'getData' is change
   useEffect(() => 
   {
      console.log("This is from UseFetch");
      getData();
   }, [url, getData])
   return [loading, data];
};

export default UseFetchTest;
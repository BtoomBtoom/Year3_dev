import UseFetchTest from "./UseFetchTest";

let url = 'https://course-api.com/javascript-store-products';
// let url = 'http://127.0.0.1:8000/api/get/2012/12/12/';

const MainTest = () => 
{
   let [y] = UseFetchTest(url);
   console.log(y);


   return (
      <div>
            <p>orem ipsum dolor sit, amet consectetur adipis
               icing elit. Deleniti aspernatur assumenda modi qu
               am nostrum, quos, praesentium consequatur, voluptas 
               provident architecto aut suscipit ea asperiores placeat 
               eveniet aliquam dolor minima? Illum.</p>
         <div>
            {/* {
               y.map((i)=>
               {
                  return(
                     <section key={i.id}>
                     {i.fields.image[0].url}
                     <br />
                     <img src={i.fields.image[0].url} alt="some-picture" />
                     <br/>
                     </section>
                  );
               })
            } */}
         </div>
      </div>
   );
}

export default MainTest;

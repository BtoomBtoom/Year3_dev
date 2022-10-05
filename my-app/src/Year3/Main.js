import UseFetch from "./UseFetch";

let url = 'https://course-api.com/javascript-store-products';

const Main = () => 
{
   let [x, y] = UseFetch(url);
   console.log(y);


   return (
      <section>
         <div>
            <h1>Hi this is from Main.js</h1>
         </div>
         <div>
            {
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
            }
         </div>
      </section>
   );
}

export default Main;

import MainTest from "./MainTest"

const Main = () => 
{

   return (
      <div>
         <div className='container px-2 py-2'>
          <div className='row'>
            <div className='col-3'>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div> 
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
            </div>

            <div className='col-9'>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><MainTest/></div>
              
            </div>

          </div>
        </div>
      </div>
   );
}

export default Main;

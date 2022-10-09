import './App.css';
import Main from './Year3/Main';
import Navbar from './Year3/Navbar';
import Footer from './Year3/Footer';



function App() {
  return (
    <div>
        <section>
          <Navbar/>
        </section>

        <div className='container px-2 py-2'>
          <div className='row'>
            <div className='col-3'>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div> 
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
            </div>

            <div className='col-9'>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
              <div className='row mx-1 my-1 rounded text-center border bg-light sub-content'><Main/></div>
              
            </div>

          </div>
        </div>

        <section>
          <Footer/>
        </section>
    </div>
  );
}

export default App;

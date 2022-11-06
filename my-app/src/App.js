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

        <section>
          <Main/>
        </section>

        <section>
          <Footer/>
        </section>
    </div>
  );
}

export default App;

import React from "react";

const Navbar = () => {
   return(
      <section>
         <nav class="navbar navbar-expand-lg navbar-dark bg-dark fixed-top">
         <div class="container-fluid">
            <a class="navbar-brand" href="https://lienminh.garena.vn/">
            <img src="https://cdn.cloudflare.steamstatic.com/steam/apps/1817070/ss_dfba6f2477bfa42be69ddfdffbd421d3943d20bf.1920x1080.jpg?t=1660316394" alt="Logo" width="30" height="24"
               class="d-inline-block align-text-top"/>
            LolXD!!!!
            </a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
               <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNavAltMarkup">
               <div class="navbar-nav">
               <a class="nav-link active" aria-current="page" href="#">Home</a>
               <a class="nav-link" href="#">Features</a>
               <a class="nav-link" href="#">Pricing</a>
               <a class="nav-link disabled">Disabled</a>
               </div>
            </div>
         </div>
         </nav>
      </section>   
   );
};

export default Navbar;
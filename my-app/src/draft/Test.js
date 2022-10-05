import React, { useState, useCallback, useMemo, useEffect } from 'react'
import { useFetch } from './UseFetch.js'

// ATTENTION!!!!!!!!!!
// I SWITCHED TO PERMANENT DOMAIN
const url = 'https://course-api.com/javascript-store-products'

// every time props or state changes, component re-renders
const calculateMostExpensive = (data) => {
  return (
    data.reduce((total, item) => {
      const price = item.fields.price
      if (price >= total) {
        total = price
      }
      return total
    }, 0) / 100
  )
}

const Index = () => {
  const {loading, products } = useFetch(url)
  const [count, setCount] = useState(0)
  const [cart, setCart] = useState(0)

  useEffect(() => {
    console.log("THIS is from Index level 1")
  })

  const addToCart = useCallback(() => {
    setCart(cart + 1)
  }, [cart])      //only when cart changes then this function is re-render

  const mostExpensive = useMemo(() => calculateMostExpensive(products), [
    products,   //chỉ khi dependency products thay đổi thì mới chạy lại hàm để đỡ tốn time, không thì vẫn giữ nguyên giá trị ở đó, không cần chạy lại hàm
  ])

  return (
    <>
      <h1>Count : {count}</h1>
      <button className='btn' onClick={() => setCount(count + 1)}>
        click me
      </button>
      <h1 style={{ marginTop: '3rem' }}>cart : {cart}</h1>
      <h1>Most Expensive : ${mostExpensive}</h1>
      <BigList products={products} addToCart={addToCart} />
    </>
  )
}

const BigList = React.memo(({ products, addToCart }) => {
  useEffect(() => {
    console.count('hello from BigList level 2');
  });

  return (
    <section className='products'>
      {products.map((product) => {
        return (
          <SingleProduct
            key={product.id}
            {...product}
            addToCart={addToCart}
          ></SingleProduct>
        )
      })}
    </section>
  )
})

const SingleProduct = ({ fields, addToCart }) => {
  let { name, price } = fields
  price = price / 100
  const image = fields.image[0].url

  useEffect(() => {
    console.count('hello from SingleProduct level 3');
  });
  return (
    <article className='product'>
      <img src={image} alt={name} />
      <h4>{name}</h4>
      <p>${price}</p>
      <button onClick={addToCart}>add to cart</button>
    </article>
  )
}
export default Index

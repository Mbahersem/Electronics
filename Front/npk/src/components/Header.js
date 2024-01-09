import React, { useState } from 'react';
import Navigation from './Navigation';
import "../styles/components/header.css";
import { NavLink } from 'react-router-dom';

function Header() {

    const [color, setColor] = useState(false);
    const changeColor = () => {

        if (window.scrollY >= 84) {
            setColor(true)
        }
        else {
            setColor(false)
        }

    }

    window.addEventListener('scroll', changeColor)

    return (

        <header id='header' className={color? 'header-bg' : ''} >
            <img src='https://cdn-icons-png.flaticon.com/128/3219/3219333.png' alt='logo'></img>
            <p>NPK Prediciton</p>
            <Navigation />
        </header>

    );

};

export default Header;
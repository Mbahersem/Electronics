import React from 'react';
import { NavLink } from 'react-router-dom';
import "../styles/components/navigation.css";

function Navigation() {
    return (
        <div className='nav'>
            <ul>
                <NavLink to="/" className={(nav) => (nav.isActive ? "div-active" : "div-inactive")}>
                    <li>Home</li>
                </NavLink>

                <NavLink to="/about" className={(nav) => (nav.isActive ? "div-active" : "div-inactive")}>
                    <li>About</li>
                </NavLink>
            </ul>
        </div>
    );
};

export default Navigation;
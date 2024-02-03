/* eslint-disable array-callback-return */
import React, { useState, useEffect } from 'react';
import axios from 'axios'
import '../styles/components/grid2.css'
import Case from './Case';

function Grid2() {
    const [data, setData] = useState([])

    const grid = [
        {"name": "Nitrogen", "acro": "N", "value": 255, "color": "rgba(189, 255, 82, 0.72)", "unit": "mg/L"},
        {"name": "Phosphorus", "acro": "P", "value": 255, "color": "rgba(189, 255, 82, 0.72)", "unit": "mg/L"},
        {"name": "Potassium", "acro": "K", "value": 255, "color": "rgba(189, 255, 82, 0.72)", "unit": "mg/L"},
        {"name": "Temperature", "acro": "T", "value": 50, "color": "rgba(119, 71, 255, 0.72)", "unit": "°C"},
        {"name": "Humidity", "acro": "H", "value": 50, "color": "rgba(0, 41, 255, 0.72)", "unit": "mL/L"},
        {"name": "pH", "acro": "P", "value": 14, "color": "rgba(166, 233, 124, 0.72)", "unit": ""}
    ]

    function handleOne () {
        const one = document.getElementById("one");
        const two = document.getElementById("two");
        two.style.zIndex = 2
        two.style.display = "block"
        one.style.display = "none"
        console.log("Switched on TWO")
    }

    function handleTwo () {
        const one = document.getElementById("one");
        const two = document.getElementById("two");
        one.style.zIndex = 2
        one.style.display = "block"
        two.style.display = "none"
        console.log("Switched on ONE")
    }

    return (
        <div className='grid2' id='grid2'>
            <ul className='cases'>
                {grid.map((data,index) => 
                    <li key={index} className={data.acro} style={{backgroundColor: data.color}}>
                        <p>{data.name + "( " + data.acro + " )"}</p>
                        <p id={data.acro}>{data.value + " " + data.unit}</p>
                    </li>
                    //<Case key={index} case={data} />
                )}
            </ul>
            <div className='result'>
                <div className='one' id='one' onClick={handleOne}>
                    <p>Prediciton: <span id='res'>Maïze</span></p>
                    <div><img alt='culture1' id='resimg1' src='https://cdn-icons-png.flaticon.com/128/6120/6120696.png'></img></div>
                </div>
                <div className='two' id='two' onClick={handleTwo}>
                    <p>Prediciton: <span id='res'>Rice</span></p>
                    <div><img alt='culture2' id='resimg2' src='https://cdn-icons-png.flaticon.com/128/3109/3109780.png'></img></div>
                </div>
            </div>
        </div>
    );
    
};

export default Grid2;
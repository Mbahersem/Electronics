import React from 'react';
import '../styles/components/grid.css';
import { useState, useEffect } from 'react';
import axios from 'axios'

function Grid() {
    useEffect(() => {
        axios.get('https://restcountries.com/v3.1/all')
        .then((res) => console.log(res))
    }, [])
    return(
        <div className='grid-container' id='grid'>
            <div className='data'>
                <div className='data1'>
                    <div className='n'>
                        <p>Nitrogen ( N )</p>
                        <p id='n'>255 mg/L</p>
                    </div>
                    <div className='p'>
                        <p>Phosporus ( P )</p>
                        <p id='p'>255 mg/L</p>
                    </div>
                    <div className='k'>
                        <p>Potassium ( K )</p>
                        <p id='k'>255 mg/L</p>
                    </div>
                </div>
                <div className='data2'>
                    <div className='temp'>
                        <p>Temperature ( C° )</p>
                        <p id='temp'>50 C°</p>
                    </div>
                    <div className='hum'>
                        <p>Humidity ( mL/L )</p>
                        <p id='hum'>50 mL/L</p>
                    </div>
                </div>
            </div>
            <div className='result'>
                <p>Prediciton: <span id='res'>Maïze</span></p>
                <div><img alt='culture' id='resimg' src='https://cdn-icons-png.flaticon.com/128/6120/6120696.png'></img></div>
            </div>
        </div>
    )
};

export default Grid;
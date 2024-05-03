/* eslint-disable array-callback-return */
import React, { useEffect, useRef, useState } from 'react';
import '../styles/components/grid2.css'

const Grid2 = ({ data, result }) => {

    var one = useRef()
    var two = useRef()

    const resGrid = {
        "maize": ["Maïze", "https://cdn-icons-png.flaticon.com/128/6120/6120696.png"],
        "bean": ["Bean", "https://cdn-icons-png.flaticon.com/128/2224/2224268.png"],
        "peanut": ["Peanut", "https://cdn-icons-png.flaticon.com/128/9849/9849878.png"],
        "rice": ["Rice", "https://cdn-icons-png.flaticon.com/128/3109/3109780.png"]
    }

    var initialGrids = [
        { "name": "Nitrogen", "acro": "N", "value": 0, "color": "rgba(189, 255, 82, 0.72)", "unit": "g/m²" },
        { "name": "Phosphorus", "acro": "P", "value": 0, "color": "rgba(189, 255, 82, 0.72)", "unit": "g/m²" },
        { "name": "Potassium", "acro": "K", "value": 0, "color": "rgba(189, 255, 82, 0.72)", "unit": "g/m²" },
        { "name": "Temperature", "acro": "T", "value": 0, "color": "rgba(119, 71, 255, 0.72)", "unit": "°C" },
        { "name": "Humidity", "acro": "H", "value": 0, "color": "rgba(0, 41, 255, 0.72)", "unit": "g/L" },
        { "name": "pH", "acro": "P", "value": 0, "color": "rgba(166, 233, 124, 0.72)", "unit": "" }
    ]

    const [grids, setGrids] = useState(initialGrids);
    const [res, setRes] = useState(result || {
        "crops": [
            "rice",
            "peanut",
            "maize",
            "bean"
        ]
    })

    console.log(res)

    useEffect(() => {

        let oldGrids = [...grids]

        var datas = []
        datas[0] = data.n
        datas[1] = data.p
        datas[2] = data.k
        datas[3] = data.t
        datas[4] = data.h
        datas[5] = data.ph

        for (let elt = 0; elt <= 5; elt++) {

            oldGrids[elt].value = datas[elt] || initialGrids[elt].value

        }
        console.log(oldGrids)
        setGrids(oldGrids)
        setRes(result)

    // eslint-disable-next-line react-hooks/exhaustive-deps
    }, [data,result])

    function handleOne() {

        two.current.style.zIndex = 2
        two.current.style.display = "block"
        one.current.style.display = "none"
        console.log("Switched on TWO")

    }

    function handleTwo() {

        one.current.style.zIndex = 2
        one.current.style.display = "block"
        two.current.style.display = "none"
        console.log("Switched on ONE")

    }

    var imone = resGrid[res["crops"][0]][1]
    var imtwo = resGrid[res["crops"][1]][1]

    return (

        <div className='grid2' id='grid2'>

            <ul className='cases'>

                {grids.map((data, index) =>
                    <li key={index} className={data.acro} style={{ backgroundColor: data.color }}>
                        <p>{data.name + "( " + data.acro + " )"}</p>
                        <p id={data.acro}>{data.value + " " + data.unit}</p>
                    </li>
                )}

            </ul>

            <div className='result'>

                <div ref={one} className='one' id='one' onClick={handleOne}>
                    <p>Prediciton: <span id='res'>{resGrid[res["crops"][0]][0]}</span></p>
                    <div><img alt='culture1' id='resimg1' src={ `${imone}` }></img></div>
                </div>

                <div ref={two} className='two' id='two' onClick={handleTwo}>
                    <p>Prediciton: <span id='res'>{resGrid[res["crops"][1]][0]}</span></p>
                    <div><img alt='culture2' id='resimg2' src={ `${imtwo}` }></img></div>
                </div>

            </div>

        </div>
    );

};

export default Grid2;
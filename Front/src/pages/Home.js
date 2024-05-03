import React, { useState } from 'react';
import { NavLink } from 'react-router-dom';
import Header from '../components/Header';
import Grid2 from '../components/Grid2';
import '../styles/pages/home.css';


function Home() {

    const [data,setData] = useState({});
    const [result, setResult] = useState({
        "crops": [
            "rice",
            "peanut",
            "maize",
            "bean"
        ]
    });

    async function refresh() {

        var requestOptions = {
            method: 'GET',
            redirect: 'follow'
        };

        const datas = await fetch("http://127.0.0.1:8000/npkmeter/npkph", requestOptions)

        setData(await datas.json())

        const results = await fetch("http://127.0.0.1:8000/npkmeter/npkph/prediction", requestOptions)

        setResult(await results.json())

        console.log(data)
        console.log(result)

    }

    /*useEffect(() => {
        refresh()
    })*/

    return (
        <div className="home">
            <Header />
            <Grid2 data={data} result={result}/>
            <div className='actualize'>

                <NavLink to='/about' className='documentation-link'>
                    Tell me more about: {result.crops[0].toUpperCase()}
                </NavLink>

                <button className='actu-btn' onClick={ refresh }>Refresh</button>

            </div>
        </div>
    );
};

export default Home;
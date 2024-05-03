import React from 'react';

function Case(props) {
    console.log(props)
    var data = props.case
    return (
        <li className={data.acro}>
            <p>{data.name + "( " + data.acro + " )"}</p>
            <p id={data.acro}>{data.value + " " + data.unit}</p>
        </li>
    );
};

export default Case;
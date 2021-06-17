import React from 'react';
import styles from './styles.module.css';

export const Select = ({ title, value, updateValue, name, }) => {
    const { options, currentValue } = value;
    const optionsComponents = Object.keys(options).map(key =>
        <option key={key}>{ key }</option>
    );

    let onChange = (e) => {
        updateValue(e.currentTarget.value, name);
    }

    return (
        <div className={styles.selectContent}>
            <div>{title}</div>
            <select value={currentValue} onChange={(e) => onChange(e)}>
                { optionsComponents }
            </select>
        </div>
    )
}
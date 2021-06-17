import React from 'react';
import styles from './styles.module.css';

export const Input = ({
    title,
    value,
    updateValue,
    className=styles.content,
    inputClassName=styles.input,
    min = 0,
    max = 5,
    type='text',
    name
}) => {
    const onChange = (e) => {
        updateValue(e.currentTarget.value, name);
    }

    return (
        <div className={className}>
            { title && <div>{ title }</div> }
            <input
                className={inputClassName}
                value={value}
                min={min}
                max={max}
                onChange={(event) => onChange(event)}
                type={type}
            />
        </div>
    )
}
import React from 'react';
import styles from './styles.module.css';

export const Button = ({ title, onClick }) => {
    return (
        <button className={styles.button} onClick={onClick}>
            {title}
        </button>
    )
};
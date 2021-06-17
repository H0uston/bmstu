import React from 'react';
import styles from './styles.module.css';

export const Text = ({ fontSize="16px", children}) => {
    return (
        <div className={styles.text} style={{fontSize}}>
            { children }
        </div>
    )
}
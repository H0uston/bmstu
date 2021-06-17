import React from 'react';
import styles from './styles.module.css';

export const Title = ({ title, className=styles.titleContent }) => {
    return (
        <div className={className}>
            { title }
        </div>
    );
}
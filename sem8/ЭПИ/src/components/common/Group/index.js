import React from 'react';
import styles from './styles.module.css';

export const Group = ({ className, title, children, hasBorder=true }) => {
    const contentClassName = hasBorder ? styles.content : styles.contentWithoutBorders;

    return (
        <div className={contentClassName + (className ? " " + className : "")}>
            <div className={styles.title}>
                {title}
            </div>
            {children}
        </div>
    )
}
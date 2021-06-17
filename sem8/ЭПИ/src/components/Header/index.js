import React from 'react';
import styles from './styles.module.css';

export const Header = () => {
    return (
        <header className={styles.headerContent}>
            <div className={styles.title}>
                Экономика Программной Инженерии
            </div>
        </header>
    )
}
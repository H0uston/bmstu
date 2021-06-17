import React from 'react';

import styles from './styles.module.css';

import { Header } from '../Header';
import { Sidebar } from '../Sidebar';
import { Content } from '../Content';

export const App = () => {
    return (
        <div className={styles.appContent}>
            <Header />
            <Sidebar />
            <Content />
        </div>
    );
};

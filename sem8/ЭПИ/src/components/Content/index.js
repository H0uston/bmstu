import React from 'react';
import { Route, Redirect } from 'react-router-dom';
import styles from './styles.module.css';
import Cocomo1Container from '../Cocomo1/container';
import { Cocomo2 } from '../Cocomo2';

export const Content = () => {
    return (
        <main className={styles.mainContent}>
            <Route exact path={'/'} render={() => <Redirect to={'/cocomo_1'} />} />
            <Route path={'/cocomo_1'} render={() => <Cocomo1Container />} />
            <Route path={'/cocomo_2'} render={() => <Cocomo2 />} />
        </main>
    )
}
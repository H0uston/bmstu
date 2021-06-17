import React from 'react';
import { NavLink } from 'react-router-dom';

import styles from './styles.module.css';

export const Sidebar = () => {
    return (
        <div className={styles.sidebarContent}>
            <NavLink className={styles.labInfo} to={'/cocomo_1'} activeClassName={styles.active}>
                COCOMO 1
            </NavLink>
            <NavLink className={styles.labInfo} to={'/cocomo_2'} activeClassName={styles.active}>
                COCOMO 2
            </NavLink>
        </div>
    )
};

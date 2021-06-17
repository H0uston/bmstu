import React from 'react';
import styles from './styles.module.css';
import { Group } from '../../common/Group';
import {PowerContainer} from "./Power/container";
import {CompositionalContainer} from "./Compositional/container";
import {EarlyDevelopmentContainer} from "./EarlyDevelopement/container";

export const Cocomo2WorkAndTime = ({

}) => {
    return (
        <Group title={'Трудозатраты и время'}>
            <PowerContainer />
            <CompositionalContainer />
            <EarlyDevelopmentContainer />
        </Group>
    )
};
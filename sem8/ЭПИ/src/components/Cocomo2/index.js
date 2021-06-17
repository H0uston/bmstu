import React from 'react';
import { Cocomo2WorkAndTime } from './Cocomo2WorkAndTime';
import { Title } from '../common/Title';
import { FunctionalPointsContainer } from './FunctionalPoints/container';

export const Cocomo2 = () => {
    return (
        <div>
            <Title title={'Лабораторная работа №7'} />
            <FunctionalPointsContainer />
            <Cocomo2WorkAndTime />
        </div>
    )
}
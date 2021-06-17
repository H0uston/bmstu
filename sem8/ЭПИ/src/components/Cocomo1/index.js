import React, { Fragment } from 'react';
import { Title } from '../common/Title';
import { EnterData } from './EnterData';
import { DrawData } from './DrawData';
import {formDecomposition, formDiagram, formDistribution} from './helpers';
import { titles } from './constants.js';

export const Cocomo1 = ({
    isResultComputed,
    result,
    ...props
}) => {
    let distribution, decomposition, diagram;
    if (isResultComputed) {
        decomposition = formDecomposition({ title: titles.rr, budget: result.budget });
        distribution = formDistribution({ title: titles.rra, work: result.work, time: result.time})
        diagram = formDiagram({ title: titles.rras, dataWt: result.dataWt });
    }

    return (
        <Fragment>
            <Title title={'Лабораторная работа №6'}/>
            <EnterData {...props} />
            { isResultComputed && (
                <DrawData
                    decomposition={decomposition}
                    distribution={distribution}
                    diagram={diagram}
                />) }
        </Fragment>
    )
}
import React from 'react';
import { SystemParamsContainer } from './SystemParams/container';
import { NormalizingFactorsContainer } from './NormalizingFactors/container';
import { Button } from '../../common/Button';
import { Group } from '../../common/Group';
import { FunctionalPointsResultContainer } from './FunctionalPointsResult/container';

export const FunctionalPoints = ({ computeFunctionalPoints, isResultComputed }) => {
    return (
        <Group title={'Вычисление функциональных точек'}>
            <SystemParamsContainer />
            <NormalizingFactorsContainer />
            <div>
                <Button title={'Расчитать'} onClick={() => computeFunctionalPoints()} />
            </div>
            { isResultComputed && <FunctionalPointsResultContainer /> }
        </Group>
    )
}
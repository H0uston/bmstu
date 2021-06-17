import React from 'react';
import { Group } from '../../../common/Group';
import { Matrix } from '../../../common/Matrix';
import { titles } from './dict';

export const NormalizingFactors = ({
    updateCharacteristics,
    ...matrix
}) => {
    const matrixComponents = Object.keys(matrix).map(m =>
        <Group key={m} title={titles[m].title} hasBorder={false}>
            <Matrix
                data={matrix[m]}
                rowHeaders={titles[m].rows.headers}
                columnHeaders={titles[m].columns.headers}
                rowTitle={titles[m].rows.title}
                columnTitle={titles[m].columns.title}
                updateValue={((position, newValue) => updateCharacteristics(m, position, newValue))}
            />
        </Group>
        )

    return (
        <Group title={'Информационные характеристики'} hasBorder={false}>
            {matrixComponents}
        </Group>
    )
}
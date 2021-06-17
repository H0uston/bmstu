import React from 'react';
import { Group } from '../../../common/Group';
import { Text } from '../../../common/Text';


export const FunctionalPointsResult = ({
    sumOfSystemParams,
    countOfFunctionalPoints,
    countOfCorrectedFunctionalPoints,
    normFactor,
}) => {
    return (
        <Group title={'Итоговый результат по функциональным точкам'}>
            <Text>
                Итоговая сумма системных параметров: { sumOfSystemParams }
            </Text>
            <Text>
                Число ненормированных функциональных точек: { countOfFunctionalPoints }
            </Text>
            <Text>
                Нормирующий фактор: { normFactor }
            </Text>
            <Text>
                Число нормированных функциональных точек: { countOfCorrectedFunctionalPoints }
            </Text>
        </Group>
    )
}
import React from 'react';
import {Text} from "../../../common/Text";

export const Result = ({p, work, time, kLOC, hasKLOC=false, hasCountOfWorkers=false}) => {
    return (
        <>
            <Text>
                {'Показатель степень (P): ' + p.toFixed(4)}
            </Text>
            <Text>
                {'Трудозатраты (чел/мес): ' + work.toFixed(2)}
            </Text>
            <Text>
                {'Время: ' + time.toFixed(2)}
            </Text>
            { hasKLOC && (
                <Text>
                    {'kLOC: ' + kLOC.toFixed(3)}
                </Text>
            )}
            { hasCountOfWorkers && (
                <Text>
                    {'Количество работников: ' + Math.ceil(+work / +time)}
                </Text>
            )}
        </>
    )
}
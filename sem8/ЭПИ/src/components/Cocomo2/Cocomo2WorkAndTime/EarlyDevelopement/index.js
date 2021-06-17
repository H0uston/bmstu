import React from 'react';
import styles from './styles.module.css';
import {Group} from "../../../common/Group";
import {Select} from "../../../common/Select";
import {titles} from "./dict";
import {Button} from "../../../common/Button";
import {Text} from "../../../common/Text";
import {Result} from "../Result";
import {Input} from "../../../common/Input";

export const EarlyDevelopment = ({
    updateEarlyDevelopment,
    updateLanguage,
    computeEarlyDevelopment,
    result,
    languages,
    ...drivers
}) => {
    const {
        p,
        earlyDevelopment: {
            work,
            time,
            isResultComputed,
            kLOC,
        },
    } = result;

    const selectors = Object.keys(drivers).map(
        k => (
            <Select
                key={k}
                title={titles[k]}
                value={drivers[k]}
                updateValue={(newValue, name) => updateEarlyDevelopment(name, newValue)}
                name={k}
            />
        )
    );

    const inputs = Object.keys(languages).map(
        k => (
            <Input
                title={k}
                value={languages[k].value}
                updateValue={(newValue, name) => updateLanguage(name, newValue)}
                key={k}
                name={k}
            />
    ));

    const sum = Object.keys(languages).reduce((acc, k) => acc + +languages[k].value, 0);
    return (
        <Group title={'Модель ранней разработки архитектуры'}>
            {selectors}
            <Group title={'Языки программирования'} hasBorder={true}>
                {inputs}
                <Text>
                    {'Итого: ' + sum}
                </Text>
            </Group>
            <Button title={'Расчитать'} onClick={() => computeEarlyDevelopment()} />
            {isResultComputed && (
                <Group title={'Результат для ранней разработки архитектуры'}>
                    <Result time={time} work={work} p={p} kLOC={kLOC} hasKLOC hasCountOfWorkers />
                </Group>
            )}
        </Group>
    )
}
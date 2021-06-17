import React from 'react';
import styles from './styles.module.css';
import {Group} from "../../../common/Group";
import {Select} from "../../../common/Select";
import {titles} from "./dict";
import {Input} from "../../../common/Input";
import {Button} from "../../../common/Button";
import {Text} from "../../../common/Text";
import {Result} from "../Result";

export const Compositional = ({
    updateCompositional,
    computeCompositional,
    teamCap,
    simpleForms,
    middleForms,
    difficultForms,
    simpleReports,
    middleReports,
    difficultReports,
    countOfModules,
    RUSE,
    result
}) => {
    const {
        p,
        compositional: {
            work,
            time,
            isResultComputed,
        },
    } = result;

    return (
        <Group title={'Композиционна модель'}>
            <Input
                title={titles.RUSE}
                value={RUSE}
                updateValue={(newValue, name) => updateCompositional(name, newValue)}
                name={'RUSE'}
            />
            <Select
                title={titles.teamCap}
                value={teamCap}
                updateValue={(newValue, name) => updateCompositional(name, newValue)}
                name={'teamCap'}
            />
            <Input
                updateValue={(newValue, name) => updateCompositional(name, newValue)}
                value={countOfModules}
                title={titles.countOfModules}
                name={'countOfModules'}
            />
            <Group title={'Экранные формы'}>
                <Input
                    title={titles.forms.simple}
                    value={simpleForms}
                    updateValue={(newValue, name) => updateCompositional(name, newValue)}
                    name={'simpleForms'}
                />
                <Input
                    title={titles.forms.middle}
                    value={middleForms}
                    updateValue={(newValue, name) => updateCompositional(name, newValue)}
                    name={'middleForms'}
                />
                <Input
                    title={titles.forms.difficult}
                    value={difficultForms}
                    updateValue={(newValue, name) => updateCompositional(name, newValue)}
                    name={'difficultForms'}
                />
            </Group>
            <Group title={'Отчёты'}>
                <Input
                    title={titles.reports.simple}
                    value={simpleReports}
                    updateValue={(newValue, name) => updateCompositional(name, newValue)}
                    name={'simpleReports'}
                />
                <Input
                    title={titles.reports.middle}
                    value={middleReports}
                    updateValue={(newValue, name) => updateCompositional(name, newValue)}
                    name={'middleReports'}
                />
                <Input
                    title={titles.reports.difficult}
                    value={difficultReports}
                    updateValue={(newValue, name) => updateCompositional(name, newValue)}
                    name={'difficultReports'}
                />
            </Group>
            <Button title={'Рассчитать'} onClick={() => computeCompositional()} />
            {isResultComputed && (
                <Group title={'Результат для композиционной модели'}>
                    <Result time={time} work={work} p={p} hasCountOfWorkers/>
                </Group>
            )}
        </Group>
    )
}
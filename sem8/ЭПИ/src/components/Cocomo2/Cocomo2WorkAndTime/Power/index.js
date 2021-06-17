import React from 'react';
import styles from './styles.module.css';
import {Group} from "../../../common/Group";
import {Select} from "../../../common/Select";
import {titles} from "./dict";

export const Power = ({
    updatePower,
    ...factors
}) => {
    const selectors = Object.keys(factors).map(
        k => (
            <Select
                key={k}
                title={titles[k]}
                value={factors[k]}
                updateValue={(newValue, name) => updatePower(name, newValue)}
                name={k}
            />
        )
    )

    return (
        <Group title={'Факторы, влияющие на показатель степени в модели'}>
            {selectors}
        </Group>
    )
}
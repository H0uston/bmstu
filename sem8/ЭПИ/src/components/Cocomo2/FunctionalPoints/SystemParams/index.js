import React from 'react';
import styles from './styles.module.css';
import { Group } from '../../../common/Group';
import { Input } from '../../../common/Input';
import { titles } from './dict';

const MIN_VALUE = 0;
const MAX_VALUE = 5;

export const SystemParams = ({
     updateSystemParams,
     ...params
}) => {
    const systemParamsComponents = Object.keys(params).map(k => (
            <Input
                title={titles[k]}
                min={MIN_VALUE}
                max={MAX_VALUE}
                value={params[k]}
                updateValue={(newValue) => updateSystemParams(k, newValue)}
                key={k}
            />
        )
    )
    return (
        <Group title={'Системные параметры'}>
            { systemParamsComponents }
        </Group>
    )
}
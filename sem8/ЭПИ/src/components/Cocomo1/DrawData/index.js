import React from 'react';
import styles from './styles.module.css';
import { Group } from '../../common/Group';
import { TableWith2Rows } from '../../common/TableWith2Rows';
import {
    PieChart,
    Pie,
    Tooltip,
    Cell,
    CartesianGrid,
    XAxis,
    YAxis,
    BarChart,
    Bar
} from 'recharts';
import {TableWith3Rows} from "../../common/TableWith3Rows";
import {Title} from "../../common/Title";

const COLORS = [
    '#0088FE',
    '#00C49F',
    '#FFBB28',
    '#FF8042',
    '#FF4442',
    '#65AFAA',
    '#3AB73C',
    '#7FCBBB'
];

const renderCustomizedLabel = ({ name, value }) => {
    return `${name} : ${value}`
};

export const DrawData = ({ decomposition, distribution, diagram }) => {
    return (
        <div className={styles.content}>
            <Group title={'Результат'}>
                <Group title={'Декомпозиция работ по созданию ПО'}>
                    <TableWith2Rows data={decomposition} hasTotal />
                    <div className={styles.graph}>
                        <PieChart width={850} height={300}>
                            <Pie
                                dataKey="value"
                                isAnimationActive={true}
                                data={decomposition}
                                cx="50%"
                                cy="50%"
                                outerRadius={100}
                                nameKey="name"
                                label={renderCustomizedLabel}
                                labelLine={true}
                                fontSize={'10px'}
                            >
                                {
                                    decomposition.map((entry, index) => (
                                        <Cell key={`cell-${index}`} fill={COLORS[index]}/>
                                    ))
                                }
                            </Pie>
                            <Tooltip />
                        </PieChart>
                    </div>
                </Group>
                <Group title={'Распределение работ и времени'}>
                    <TableWith3Rows data={distribution} hasTotal />
                    <div className={styles.graph}>
                        <Title title={'Человеко-месяцы'} />
                        <PieChart width={850} height={300}>
                            <Pie
                                dataKey="value"
                                isAnimationActive={true}
                                data={distribution.work}
                                cx="50%"
                                cy="50%"
                                outerRadius={100}
                                nameKey="name"
                                label={renderCustomizedLabel}
                                labelLine={true}
                                fontSize={'10px'}
                            >
                                {
                                    decomposition.map((entry, index) => (
                                        <Cell key={`cell-${index}`} fill={COLORS[index]}/>
                                    ))
                                }
                            </Pie>
                            <Tooltip />
                        </PieChart>
                        <Title title={'Месяцы'} />
                        <PieChart width={850} height={300}>
                            <Pie
                                dataKey="value"
                                isAnimationActive={true}
                                data={distribution.time}
                                cx="50%"
                                cy="50%"
                                outerRadius={100}
                                nameKey="name"
                                label={renderCustomizedLabel}
                                labelLine={true}
                                fontSize={'10px'}
                            >
                                {
                                    decomposition.map((entry, index) => (
                                        <Cell key={`cell-${index}`} fill={COLORS[index]}/>
                                    ))
                                }
                            </Pie>
                            <Tooltip />
                        </PieChart>
                    </div>
                </Group>
                <Group title={'Диаграмма привлечения сотрудников'}>
                    <BarChart
                        width={800}
                        height={300}
                        data={diagram}
                    >
                        <CartesianGrid strokeDasharray="3 3"/>
                        <XAxis dataKey='name' fontSize={'10px'}  />
                        <YAxis />
                        <Tooltip />
                        <Bar dataKey='value' fill="#8884d8" />
                    </BarChart>
                </Group>
            </Group>
        </div>
    )
};
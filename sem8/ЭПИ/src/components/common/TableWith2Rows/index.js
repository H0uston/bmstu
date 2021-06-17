import React from 'react';
import styles from './styles.module.css';

const HEADERS = [
    'Вид деятельности',
    'Бюджет'
];

export const TableWith2Rows = ({ data, hasTotal }) => {

    const headers = HEADERS.map((h, index) => <div key={index} className={styles.tableHeader}>{h}</div>);
    const body = [];
    for (let row of data) {
        body.push(
            <div key={row.name} className={styles.tableRow}>
                <div className={styles.elem}>{row.name}</div>
                <div className={styles.elem}>{row.value}</div>
            </div>
        )

    }

    let sum = 0;

    if (hasTotal) {
        for (let row of data) {
            sum += +row.value;
        }

    }

    return (
        <div className={styles.border}>
            <div className={styles.table}>
                <div className={styles.tableHeaders + " " + styles.tableRow}>
                    {headers}
                </div>
                <div>
                    <div className={styles.tableRowEval}>
                        {body}
                        {hasTotal && (
                            <div className={styles.tableRow}>
                                <div className={styles.elem}>{'Итого'}</div>
                                <div className={styles.elem}>{sum.toFixed(2)}</div>
                            </div>
                        )}
                    </div>
                </div>
            </div>
        </div>
    );
}
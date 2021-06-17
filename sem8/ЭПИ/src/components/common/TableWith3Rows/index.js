import React from 'react';
import styles from './styles.module.css';

const HEADERS = [
    'Вид деятельности',
    'Трудозатраты',
    'Время'
];

export const TableWith3Rows = ({data: { work, time }, hasTotal }) => {
    const headers = HEADERS.map((h, index) => <div key={index} className={styles.tableHeader}>{h}</div>);
    const body = [];
    for (let i = 0; i < work.length; i++) {
        body.push(
            <div key={work[i].name} className={styles.tableRow}>
                <div className={styles.elem}>{work[i].name}</div>
                <div className={styles.elem}>{work[i].value}</div>
                <div className={styles.elem}>{time[i].value}</div>
            </div>
        )
    }

    let sumW = 0;
    let sumT = 0;

    if (hasTotal) {
        for (let i = 0; i < work.length; i++) {
            sumW += +(work[i].value).toFixed(2);
            sumT += +(time[i].value).toFixed(2);
        }
    }

    let sumWWithoutPadt = +(sumW - work[0].value).toFixed(2);
    let sumTWithoutPadt = +(sumT - time[0].value).toFixed(2);

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
                            <>
                                <div className={styles.tableRow}>
                                    <div className={styles.elem}>{'Итого без планирования'}</div>
                                    <div className={styles.elem}>{sumWWithoutPadt.toFixed(2)}</div>
                                    <div className={styles.elem}>{sumTWithoutPadt.toFixed(2)}</div>
                                </div>
                                <div className={styles.tableRow}>
                                    <div className={styles.elem}>{'Итого'}</div>
                                    <div className={styles.elem}>{sumW.toFixed(2)}</div>
                                    <div className={styles.elem}>{sumT.toFixed(2)}</div>
                                </div>
                            </>
                        )}
                    </div>
                </div>
            </div>
        </div>
    );
}
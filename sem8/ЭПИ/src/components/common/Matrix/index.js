import React from 'react';
import styles from "./styles.module.css";
import { Input } from '../Input';

export const Matrix = ({
    data,
    columnTitle,
    rowTitle,
    rowHeaders,
    columnHeaders,
    updateValue,
}) => {
    const columnTitleComponent = <div className={styles.columnTitle}>{columnTitle}</div>;
    const rowTitleComponent = <div className={styles.rowTitle}>{rowTitle}</div>;
    const rowHeadersComponents = rowHeaders.map(rh => <div key={rh}>{rh}</div>);
    const columnHeadersComponents = columnHeaders.map(ch => <div key={ch}>{ch}</div>)

    const body = [];
    for (let i = 0; i < data.length; i++) {
        body.push(data[i].map((elem, index) =>
            <Input
                key={index}
                value={elem}
                updateValue={(newValue) => updateValue({row: i, column: index}, newValue)}
            />
        ))

    }

    return (
        <div className={styles.content}>
            {columnTitleComponent}
            {rowTitleComponent}
            <div className={styles.columnHeader}>
                {columnHeadersComponents}
            </div>
            <div className={styles.rowHeader}>
                {rowHeadersComponents}
            </div>
            <div className={styles.elements}>
                {body}
            </div>
        </div>
    )
}
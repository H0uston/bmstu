import React from 'react';
import styles from './styles.module.css';
import { Input } from '../../common/Input';
import { Select } from '../../common/Select';
import { Group } from '../../common/Group';
import { titles } from '../constants';
import { Button } from '../../common/Button';
import { computeTotal } from '../helpers';

export const EnterData = ({
    kloc,
    setKloc,
    languages,
    setLanguage,
    rely,
    setRely,
    data,
    setData,
    cplx,
    setCplx,
    time,
    setTime,
    stor,
    setStor,
    virt,
    setVirt,
    turn,
    setTurn,
    acap,
    setAcap,
    aexp,
    setAexp,
    pcap,
    setPcap,
    vexp,
    setVexp,
    lexp,
    setLexp,
    modp,
    setModp,
    tool,
    setTool,
    sced,
    setSced,
    mode,
    setMode,
    computeResult,
    tAn,
    setTAN,
    tProj,
    setTPROJ,
    tProg,
    setTPROG,
    tTest,
    setTTEST,
    tVer,
    setTVER,
    tOff,
    setTOFF,
    tMng,
    setTMNG,
    tMnl,
    setTMNL,
    mAn,
    mProj,
    mProg,
    mTest,
    mVer,
    mOff,
    mMng,
    mMnl,
    wpadt,
    setWPADT,
    tpadt,
    setTPADT,
    wpp,
    setWPP,
    tpp,
    setTPP,
    wdp,
    setWDP,
    tdp,
    setTDP,
    wkatom,
    setWKATOM,
    tkatom,
    setTKATOM,
    tiat,
    setTIAT,
    wiat,
    setWIAT,
}) => {

    const drp = [
        tAn,
        tProj,
        tProg,
        tTest,
        tVer,
        tOff,
        tMng,
        tMnl
    ];

    const totalDrpCount = computeTotal(drp);

    const rraw = [
        wpadt,
        wpp,
        wdp,
        wkatom,
        wiat
    ];

    const totalRrawCount = computeTotal(rraw);

    const rrat = [
        tpadt,
        tpp,
        tdp,
        tkatom,
        tiat
    ];

    const totalRratCount = computeTotal(rrat);

    return (
        <div className={styles.enterDataContent}>
            <Group title={'Ввод данных'}>
                <Input
                    title={titles.kloc}
                    value={kloc}
                    updateValue={setKloc}
                />
                <Select
                    title={titles.lang}
                    value={languages}
                    updateValue={setLanguage}
                />
                <Select
                    title={titles.mode}
                    value={mode}
                    updateValue={setMode}
                />
                <Group title={titles.app.title}>
                    <Select
                        title={titles.app.rely}
                        value={rely}
                        updateValue={setRely}
                    />
                    <Select
                        title={titles.app.data}
                        value={data}
                        updateValue={setData}
                    />
                    <Select
                        title={titles.app.cplx}
                        value={cplx}
                        updateValue={setCplx}
                    />
                </Group>
                <Group title={titles.ac.title}>
                    <Select
                        title={titles.ac.time}
                        value={time}
                        updateValue={setTime}
                    />
                    <Select
                        title={titles.ac.stor}
                        value={stor}
                        updateValue={setStor}
                    />
                    <Select
                        title={titles.ac.virt}
                        value={virt}
                        updateValue={setVirt}
                    />
                    <Select
                        title={titles.ac.turn}
                        value={turn}
                        updateValue={setTurn}
                    />
                </Group>
                <Group title={titles.ap.title}>
                    <Select
                        title={titles.ap.acap}
                        value={acap}
                        updateValue={setAcap}
                    />
                    <Select
                        title={titles.ap.aexp}
                        value={aexp}
                        updateValue={setAexp}
                    />
                    <Select
                        title={titles.ap.pcap}
                        value={pcap}
                        updateValue={setPcap}
                    />
                    <Select
                        title={titles.ap.vexp}
                        value={vexp}
                        updateValue={setVexp}
                    />
                    <Select
                        title={titles.ap.lexp}
                        value={lexp}
                        updateValue={setLexp}
                    />
                </Group>
                <Group title={titles.apr.title}>
                    <Select
                        title={titles.apr.modp}
                        value={modp}
                        updateValue={setModp}
                    />
                    <Select
                        title={titles.apr.tool}
                        value={tool}
                        updateValue={setTool}
                    />
                    <Select
                        title={titles.apr.sced}
                        value={sced}
                        updateValue={setSced}
                    />
                </Group>
                <Group title={titles.drp.title}>
                    <Input title={titles.drp.tAn} value={tAn} updateValue={setTAN} />
                    <Input title={titles.drp.tProj} value={tProj} updateValue={setTPROJ} />
                    <Input title={titles.drp.tProg} value={tProg} updateValue={setTPROG} />
                    <Input title={titles.drp.tTest} value={tTest} updateValue={setTTEST} />
                    <Input title={titles.drp.tVer} value={tVer} updateValue={setTVER} />
                    <Input title={titles.drp.tOff} value={tOff} updateValue={setTOFF} />
                    <Input title={titles.drp.tMng} value={tMng} updateValue={setTMNG} />
                    <Input title={titles.drp.tMnl} value={tMnl} updateValue={setTMNL} />
                    <div className={styles.total + (totalDrpCount === 100 ? '' : (' + ' + styles.wrongTotal))}>
                        {titles.rr.total}{totalDrpCount}
                    </div>
                </Group>
                <Group title={titles.rraw.title}>
                    <Input title={titles.rraw.wpadt} value={wpadt} updateValue={setWPADT} />
                    <Input title={titles.rraw.wpp} value={wpp} updateValue={setWPP} />
                    <Input title={titles.rraw.wdp} value={wdp} updateValue={setWDP} />
                    <Input title={titles.rraw.wkatom} value={wkatom} updateValue={setWKATOM} />
                    <Input title={titles.rraw.wiat} value={wiat} updateValue={setWIAT} />
                    <div className={styles.total + (totalRrawCount === 100 ? '' : (' + ' + styles.wrongTotal))}>
                        {titles.rraw.total}{totalRrawCount}
                    </div>
                </Group>
                <Group title={titles.rrat.title}>
                    <Input title={titles.rrat.tpadt} value={tpadt} updateValue={setTPADT} />
                    <Input title={titles.rrat.tpp} value={tpp} updateValue={setTPP} />
                    <Input title={titles.rrat.tdp} value={tdp} updateValue={setTDP} />
                    <Input title={titles.rrat.tkatom} value={tkatom} updateValue={setTKATOM} />
                    <Input title={titles.rrat.tiat} value={tiat} updateValue={setTIAT} />
                    <div className={styles.total + (totalRratCount === 100 ? '' : (' + ' + styles.wrongTotal))}>
                        {titles.rraw.total}{totalRratCount}
                    </div>
                </Group>
                <Button title={titles.btn} onClick={computeResult} />
            </Group>
        </div>
    )
}

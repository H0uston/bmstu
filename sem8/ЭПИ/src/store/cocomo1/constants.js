export const LANGUAGES = {
    options: {
        'Assembler': 1,
        'C': 2.5,
        'Cobol': 3,
        'Fortran': 3,
        'Pascal': 3.5,
        'C++': 6,
        'Java': 6,
        'Ada 95': 6.5,
        'Access': 8.5,
        'Delphi Pascal': 11,
        'Cobra': 16,
    },
    currentValue: 'Assembler',
};

export const RELY = {
    options: {
        'Очень низкий': 0.75,
        'Низкий': 0.86,
        'Номинальный': 1,
        'Высокий': 1.15,
        'Очень высокий': 1.4,
    },
    currentValue: 'Номинальный',
};

export const DATA = {
    options: {
        'Низкий': 0.94,
        'Номинальный': 1,
        'Высокий': 1.08,
        'Очень высокий': 1.16,
    },
    currentValue: 'Номинальный',
};

export const CPLX = {
    options: {
        'Очень низкий': 0.7,
        'Низкий': 0.85,
        'Номинальный': 1,
        'Высокий': 1.15,
        'Очень высокий': 1.3,
    },
    currentValue: 'Номинальный',
};

export const TIME = {
    options: {
        'Номинальный': 1,
        'Высокий': 1.11,
        'Очень высокий': 1.5,
    },
    currentValue: 'Номинальный',
};

export const STOR = {
    options: {
        'Номинальный': 1,
        'Высокий': 1.06,
        'Очень высокий': 1.21,
    },
    currentValue: 'Номинальный',
};

export const VIRT = {
    options: {
        'Низкий': 0.87,
        'Номинальный': 1,
        'Высокий': 1.15,
        'Очень высокий': 1.3,
    },
    currentValue: 'Номинальный',
};

export const TURN = {
    options: {
        'Низкий': 0.87,
        'Номинальный': 1,
        'Высокий': 1.07,
        'Очень высокий': 1.15,
    },
    currentValue: 'Номинальный',
};

export const ACAP = {
    options: {
        'Очень низкий': 1.46,
        'Низкий': 1.19,
        'Номинальный': 1,
        'Высокий': 0.86,
        'Очень высокий': 0.71,
    },
    currentValue: 'Номинальный',
};

export const AEXP = {
    options: {
        'Очень низкий': 1.29,
        'Низкий': 1.15,
        'Номинальный': 1,
        'Высокий': 0.91,
        'Очень высокий': 0.82,
    },
    currentValue: 'Номинальный',
};

export const PCAP = {
    options: {
        'Очень низкий': 1.42,
        'Низкий': 1.17,
        'Номинальный': 1,
        'Высокий': 0.86,
        'Очень высокий': 0.7,
    },
    currentValue: 'Номинальный',
};

export const VEXP = {
    options: {
        'Очень низкий': 1.21,
        'Низкий': 1.1,
        'Номинальный': 1,
        'Высокий': 0.9,
    },
    currentValue: 'Номинальный',
};

export const LEXP = {
    options: {
        'Очень низкий': 1.14,
        'Низкий': 1.07,
        'Номинальный': 1,
        'Высокий': 0.95,
    },
    currentValue: 'Номинальный',
};

export const MODP = {
    options: {
        'Очень низкий': 1.24,
        'Низкий': 1.1,
        'Номинальный': 1,
        'Высокий': 0.91,
        'Очень высокий': 0.82,
    },
    currentValue: 'Номинальный',
};

export const TOOL = {
    options: {
        'Очень низкий': 1.24,
        'Низкий': 1.1,
        'Номинальный': 1,
        'Высокий': 0.91,
        'Очень высокий': 0.82,
    },
    currentValue: 'Номинальный',
};

export const SCED = {
    options: {
        'Очень низкий': 1.23,
        'Низкий': 1.08,
        'Номинальный': 1,
        'Высокий': 1.04,
        'Очень высокий': 1.1,
    },
    currentValue: 'Номинальный',
};

export const SIMPLE_MODE = 'SIMPLE-MODE';
export const INTER_MODE = 'INTER-MODE';
export const BUILDIN_MODE = 'BUILDIN-MODE';

export const mode = {
    options: {
        'Обычный': SIMPLE_MODE,
        'Промежуточный': INTER_MODE,
        'Встроенный': BUILDIN_MODE,
    },
    currentValue: 'Обычный',
}

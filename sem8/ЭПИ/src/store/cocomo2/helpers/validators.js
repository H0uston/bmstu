export const minAndMaxValidatorCreator = (min, max) => {
    return (value) => {
        if (value < min) {
            return min;
        } else if (value > max) {
            return max;
        } else {
            return value;
        }
    }
}

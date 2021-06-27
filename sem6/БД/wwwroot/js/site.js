// Код валидации формы

(function () {
    function validateNumber(value, min, max) {
        value = parseInt(value);

        if (isNaN(value)) {
            return false;
        }

        if (min && parseInt(min) > value) {
            return false;
        }

        if (max && parseInt(max) < value) {
            return false;
        }

        return true;
    }

    function validateDate(value) {
        let arrayOfStrings = value.split('.');
        let day = parseInt(arrayOfStrings[0]);
        let month = parseInt(arrayOfStrings[1]);
        let year = parseInt(arrayOfStrings[2]);

        if (isNaN(day) || isNaN(month) || isNaN(year)) {
            return false;
        }

        if (month <= 0 || month >= 13) {
            return false;
        } else if ((
            (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day <= 0 || day > 31))) {
            return false;
        } else if ((
            (month == 4 || month == 6 || month == 9 || month == 11) && (day <= 0 || day >= 30))) {
            return false;
        } else if ((month == 2) && (day <= 0 || day >= 29)) {
            return false;
        }

        if (year < 1900 || year > 2020) {
            return false;
        } 

        return true;
    }

    function validateRegexp(value, pattern, flags) {
        return new RegExp(pattern, flags).test(value);
    }

    function validateValue(value, dataset) {
        switch (dataset.validator) {
            case 'number':
                return validateNumber(value, dataset.validatorMin, dataset.validatorMax);
            case 'letters':
                return validateRegexp(value, '^[a-zа-яё ]+$', 'i');
            case 'regexp':
                return validateRegexp(value, dataset.validatorPattern);
            case 'date':
                return validateDate(value);
            case 'email':
                return validateRegexp(value, /^[a-z0-9.]+@[a-z.]+\.[a-z]+$/, 'i');
            default:
                return true;
        }
    }

    function checkInput(input) {
        let value = input.value;
        if (input.dataset.hasOwnProperty('required') && !value) {
            return false;
        }

        let validator = input.dataset.validator;

        return (validator && value)
            ? validateValue(value, input.dataset)
            : true;
    }

    window.validateForm = function (options) {
        let form = document.getElementById(options.formId);
        let inputs = Array.from(document.querySelectorAll('#' + options.formId + ' input'));

        form.addEventListener('focus', function (event) {
            let target = event.target;
            if (target.tagName === 'INPUT') {
                target.classList.remove(options.inputErrorClass);
            }
        }, true);

        form.addEventListener('blur', function (event) {
            let target = event.target;
            if (target.tagName === 'INPUT') {
                if (!checkInput(target)) {
                    target.classList.add(options.inputErrorClass);
                }
            }
        }, true);

        form.addEventListener('submit', function (event) {
            form.classList.remove(options.formValidClass);
            form.classList.remove(options.formInvalidClass);
            form.classList.remove(options.modelInvalidClass);

            let hasError = false;
            for (let i = 0; i < inputs.length; i++) {
                let input = inputs[i];

                if (input.classList.contains("password")) {
                    var password = input;
                } else if (input.classList.contains("confirm-password")) {
                    var confirm_password = input;
                }

                if (!checkInput(input)) {
                    input.classList.add(options.inputErrorClass);
                    hasError = true;
                }


            }

            if (hasError || password.value != confirm_password.value) {
                form.classList.add(options.formInvalidClass);
                event.preventDefault();
            }
        });
    };

}());

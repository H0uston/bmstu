import {categoryAPI} from "../../API/categoryAPI";
import {SET_CATEGORIES, SET_PRODUCTS, setCategories, setProducts} from "./homeAction";
import {productAPI} from "../../API/productAPI";
import {setIsFetching} from "../fetchingReducer/fetchingAction";

let initialState = {
    categories: null,
    products: null,
    countOfCategories: 3,
};


const homeReducer = (state=initialState, action) => {
    let stateCopy = {...state};

    switch (action.type) {
        case (SET_CATEGORIES):
            stateCopy.categories = action.categories;
            break;
        case (SET_PRODUCTS):
            stateCopy.products = action.products;
            break;
        default:
            break;
    }

    return stateCopy;
};

export const getCategories = () => async (dispatch) => {
    dispatch(setIsFetching(true));
    let response = await categoryAPI.fetchAll(1, 16);

    if (response.status === 200) {
        let categories = await response.json();
        let products = [];

        for (let category of categories) {
            for (let categoryCollection of category.categoryCollection) {
                let resp = await productAPI.fetchProduct(categoryCollection.productId);

                if (resp.status === 200) {
                    let product = await resp.json();
                    products.push(product);
                } else {
                    throw Error(response.statusText);
                }
            }
        }
        dispatch(setCategories(categories));
        dispatch(setProducts(products));
        dispatch(setIsFetching(false));
    } else {
        throw Error(response.statusText);
    }
};

export default homeReducer;
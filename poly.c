#include "poly.h"


polyElement* create(int coeff, int degree)
{
    polyElement* polynom = (polyElement*)malloc(sizeof(polyElement));
    polynom->coeff = coeff;
    polynom->degree = degree;
    polynom->next = NULL;
    return polynom;
}

void summary(polyElement* elem1, polyElement* elem2)
{
    polyElement* count = elem1;
    while (count->next != NULL)
        count = count->next;
    
    for (polyElement* elemSecond = elem2; elemSecond != NULL; elemSecond = elemSecond->next)
    {
        int add = 0;
        for (polyElement* elemFirst = elem1; elemFirst != NULL; elemFirst = elemFirst->next)
        {
            if (elemFirst->degree == elemSecond->degree)
            {
                elemFirst->coeff += elemSecond->coeff;
                add = 1;
                break;
            }
        }
        if (add)
            continue;
        polyElement* temp = (polyElement*)malloc(sizeof(polyElement));
        temp->coeff = elemSecond->coeff;
        temp->degree = elemSecond->degree;
        temp->next = NULL;
        count->next = temp;
        count = count->next;
    }
}

void diff(polyElement* elem1, polyElement* elem2)
{
    for (polyElement* temp = elem2; temp != NULL; temp = temp->next)
    {
        temp->coeff *= -1;
    }
    summary(elem1, elem2);
}

polyElement* mult(polyElement* elem1, polyElement* elem2)
{
    polyElement* temp = create(0, 1);
    for (polyElement* elemFirst = elem1; elemFirst != NULL; elemFirst = elemFirst->next)
    {
        for (polyElement* elemSecond = elem2; elemSecond != NULL; elemSecond = elemSecond->next)
        {
            summary(temp, 
                    create(elemFirst->coeff * elemSecond->coeff, 
                           elemFirst->degree + elemSecond->degree));
        }
    }
    return temp;
}

void mult_coeff(polyElement* elem, int coeff)
{
    elem->coeff *= coeff;
}

polyElement* degree(polyElement* elem, int degree)
{
    polyElement* temp = create(1, 0);
    for (int i = 0; i < degree; i++) 
    {
        temp = mult(temp, elem);
    }
    return temp;
}

polyElement* polydegree(polyElement* elem1, polyElement* elem2)
{
    return degree(elem1, elem2->coeff);
}

int calc_degree(int value, int deg)
{
    return pow(value, deg);
}

void swap(polyElement* a, polyElement* b) 
{
    int temp_coeff = a->coeff;
    int temp_degree = a->degree;
    a->coeff = b->coeff;
    a->degree = b->degree;
    b->coeff = temp_coeff;
    b->degree = temp_degree;
}

void polysort(polyElement* poly) 
{
    polyElement *current, *index;
    int temp_coeff, temp_degree;

    if (poly == NULL)
        return;

    for (current = poly; current->next != NULL; current = current->next) 
    {
        for (index = current->next; index != NULL; index = index->next) 
        {
            if (current->degree < index->degree) swap(current, index);
        }
    }
}

void print(polyElement* poly)
{
    int counter = 0;
    for (polyElement* elem = poly; elem != NULL; elem = elem->next)
    {
        if (elem->coeff == 0)
            continue;
        if (elem->degree == 0)
        {   
            if (elem->coeff > 1 && counter != 0)
                printf("+%d", elem->coeff);
            else
                printf("%d", elem->coeff);
        }
        else if (elem->degree == 1)
        {
            if (elem->coeff > 1 && counter != 0)
                printf("+%dx", elem->coeff);
            else if (elem->coeff == 1)
                printf("x");
            else
                printf("%dx", elem->coeff);
        }
        else
        {
            if (elem->coeff > 1 && counter != 0)
                printf("+%dx^%d", elem->coeff, elem->degree);
            else if (elem->coeff == 1)
                printf("x^%d", elem->degree);
            else
                printf("%dx^%d", elem->coeff, elem->degree);
        }
        counter++;
    }
    printf("\n");
}
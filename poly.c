#include "poly.h"

polyVariable polyVariables;

void init_structs()
{
    char temp[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for (int i = 0; i < VARCOUNTS; i++)
        polyVariables.varnames[i] = temp[i];
}

int search_index(char varname)
{
    int index = 0;
    for (index = 0; index < VARCOUNTS; index++)
    {
        if (varname == polyVariables.varnames[index])
            break;
    }
    if (index == VARCOUNTS)
        error_msg("variable not found");
    return index;
}

void set_polynom(char varname, polyElement* polynom)
{
    int index = search_index(varname);
    polyVariables.polynoms[index] = *polynom;
}

polyElement* search_polynom(char varname)
{
    int index = search_index(varname);
    return &polyVariables.polynoms[index];
}

void print_var(char varname)
{
    polyElement* tempPrint = search_polynom(varname);
    print(tempPrint);
}

polyElement* copy_polynoms(polyElement* dest, polyElement* src)
{
    polyElement* tempDest = dest;
    for (polyElement* tempSrc = src; tempSrc != NULL; tempSrc = tempSrc->next)
    {
        tempDest->coeff = tempSrc->coeff;
        tempDest->degree = tempSrc->degree;
        tempDest->variable = tempSrc->variable;
        tempDest->next = tempSrc->next;
        if (tempDest != NULL)
            tempDest = (polyElement*)malloc(sizeof(polyElement));
        tempDest = tempDest->next;
    }
    return dest;
}

polyElement* create(char variable, int coeff, int degree)
{
    polyElement* polynom = (polyElement*)malloc(sizeof(polyElement));
    polynom->variable = variable;
    polynom->coeff = coeff;
    polynom->degree = degree;
    polynom->next = NULL;
    return polynom;
}

int check_variables(polyElement* elem1, polyElement* elem2)
{
    for (polyElement* elemFirst = elem1; elemFirst != NULL; elemFirst = elemFirst->next)
    {
        for (polyElement* elemSecond = elem2; elemSecond != NULL; elemSecond = elemSecond->next)
        {
            if (elemFirst->variable != elemSecond->variable)
            {
                if (elemFirst->variable == 0 || elemSecond->variable == 0)
                    continue;
                return 0;
            }
        }
    }
    return 1;
}

void summary(polyElement* elem1, polyElement* elem2)
{
    if (!check_variables(elem1, elem2))
        error_msg("operations with different variables are not possible");

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
        temp->variable = elemSecond->variable;
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
    polyElement* temp = create(elem1->variable, 0, 1);
    for (polyElement* elemFirst = elem1; elemFirst != NULL; elemFirst = elemFirst->next)
    {
        for (polyElement* elemSecond = elem2; elemSecond != NULL; elemSecond = elemSecond->next)
        {
            summary(temp, 
                    create(elemFirst->variable, elemFirst->coeff * elemSecond->coeff, 
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
    polyElement* temp = create(elem->variable, 1, 0);
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
    char temp_variable = a->variable;
    a->coeff = b->coeff;
    a->degree = b->degree;
    a->variable = b->variable;
    b->coeff = temp_coeff;
    b->degree = temp_degree;
    b->variable = temp_variable;
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
                printf("+%d%c", elem->coeff, elem->variable);
            else if (elem->coeff == 1)
                printf("%c", elem->variable);
            else
                printf("%d%c", elem->coeff, elem->variable);
        }
        else
        {
            if (elem->coeff > 1 && counter != 0)
                printf("+%d%c^%d", elem->coeff, elem->variable, elem->degree);
            else if (elem->coeff == 1)
                printf("%c^%d", elem->variable, elem->degree);
            else
                printf("%d%c^%d", elem->coeff, elem->variable, elem->degree);
        }
        counter++;
    }
    printf("\n");
}
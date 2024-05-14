#include "poly.h"

polyVariable polyVariables;

void init_structs()
{
    char tempNames[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for (int i = 0; i < VARCOUNTS; i++)
        polyVariables.varnames[i] = tempNames[i];
    memset(polyVariables.statuses, 0, sizeof(char) * VARCOUNTS);
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
    polyVariables.statuses[index] = 1;
    polyVariables.polynoms[index] = *polynom;
}

polyElement* search_polynom(char varname)
{
    int index = search_index(varname);
    if (polyVariables.statuses[index] == 0)
        error_msg("variable does not exists");
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

polyElement* summary(polyElement* elem1, polyElement* elem2)
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
    polysort(elem1);
    clean(elem1);
    return elem1;
}

polyElement* diff(polyElement* elem1, polyElement* elem2)
{
    if (!check_variables(elem1, elem2))
        error_msg("operations with different variables are not possible");
    
    for (polyElement* temp = elem2; temp != NULL; temp = temp->next)
    {
        temp->coeff *= -1;
    }
    summary(elem1, elem2);
    return elem1;
}

polyElement* mult(polyElement* elem1, polyElement* elem2)
{
    if (!check_variables(elem1, elem2))
        error_msg("operations with different variables are not possible");
    
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
    polysort(temp);
    clean(temp);
    return temp;
}

polyElement* operation(char sign, polyElement* elem1, polyElement* elem2)
{
    if (sign == '+')
        return summary(elem1, elem2);
    else if (sign == '-')
        return diff(elem1, elem2);
}

void mult_coeff(polyElement* elem, int coeff)
{
    elem->coeff *= coeff;
}

polyElement* degree(polyElement* elem, int degree)
{
    if (degree < 0)
        error_msg("negative degree");
    if (elem->coeff == 0 && degree == 0)
        error_msg("expression is an indeterminacy");
    polyElement* temp = create(elem->variable, 1, 0);
    for (int i = 0; i < degree; i++) 
    {
        temp = mult(temp, elem);
    }
    polysort(temp);
    clean(temp);
    return temp;
}

int check_monomial(polyElement* poly)
{
    polyElement *current;
    for (current = poly; current != NULL; current = current->next) 
    {
        if (current->variable != 0)
            return 0;
    }
    return 1;
}

polyElement* polydegree(polyElement* elem1, polyElement* elem2)
{
    if (!check_monomial(elem2))
        error_msg("polynomial in degree");
    return degree(elem1, elem2->coeff);
}

int calc_degree(int value, int deg)
{
    if (deg < 0)
        error_msg("negative degree");
    return pow(value, deg);
}

void debug_print(polyElement* a)
{
    printf("coeff: %d, degree: %d, variable: %c, next: %p\n",
    a->coeff, a->degree, a->variable, a->next);
}

void clean(polyElement* poly)
{
    polyElement *current;
    for (current = poly; current != NULL; current = current->next) 
    {
        if (current->next != NULL)
        {
            if (current->next->coeff == 0)
            {
                polyElement *temp = current->next;
                polyElement *result = NULL;
                while (temp != NULL)
                {
                    if (temp->coeff == 0)
                    {
                        polyElement *ptr = temp->next;
                        free(temp);
                        temp = ptr;
                    }
                    else
                    {
                        result = temp;
                        break;
                    }
                }
                current->next = result;
                break;
            }
        }
    }
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
            if (current->degree < index->degree || current->coeff == 0) swap(current, index);
        }
    }
}

void print(polyElement* poly)
{
    int counter = 0;
    for (polyElement* elem = poly; elem != NULL; elem = elem->next)
    {
        if (elem->coeff == 0)
            printf("'%d'", elem->coeff);
        else if (elem->degree == 0)
        {   
            if (elem->coeff >= 1 && counter != 0)
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
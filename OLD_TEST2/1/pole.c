typedef TStackElement int;

struct TStack {
    size_t iCount, iCapacity;
    TStackElement* iValues;
};

void stack_init (struct TStack* aStack) {
    if (aStack != NULL) {
        aStack->iCount = aStack.iCapacity = 0;
        aStack->iValues = NULLů
    }
}

bool stack_push (struct TStack* aStack, TStackElement aValue) {
    if (aStack == NULL)
        return false;
    if (aStack->iCapacity == 0) {
        aStack->iCapacity += 1;
        aStack->iValues = malloc(sizeof(TStackElement));
        aStack->iValues[aStack->iCount] = aValue;
        aStack->iCount += 1;
        return true;
    }
    if (aStack->iCount == aStack->iCapacity) {
        aStack->iCapacity *= 2;
        //aStack–>iValues = realloc(aStack->iValues, aStack->iCapacity);                // toto by mělo fungovat, ale na testu se vyskytla nějaká chyba, proto využil jsem new_values a cyklus for
        TStackElement* new_values = malloc(aStack->iCapacity * sizeof(TStackElement));
        for (int i = 0; i < aStack->iCapacity / 2; i++)
            new_values[i] = aStack->iValues[i];
        
        //aStack->iValues = NULL;
        //nebo                          // na testu jsem to nenapsal, proto nevím, jak by to melo být správně. zkus obě varianty =)
        free(aStack->iValues);
        
        aStack->iValues = new_values;
        aStack->iValues[aStack->iCount] = aValue;
        aStack->iCount += 1;
        return true;
    }
    aStack->iValues[aStack->iCount] = aValue;
    aStack->iCount += 1;
    return true;
}

bool stack_pop (struct TStack* aStack) {
    if (aStack == NULL)
        return false;
    aStack->iCount -= 1;
    if (aStack->iCount == 0) {
        stack_destroy(aStack);      // toto jsem taky neměl ideálně napsané, tak že nevím, jestli to bude moc správně, ale podle mě bude to správně
        return true;                // možná tady musí být prostě "return true"
    }
    if (aStack->iCapacity / aStack->iCount == 4) {
        aStack->iCapacity /= 2;
        //aStack->iValues = realloc(aStack->iValues, aStack->iCapacity);   // stejný problém, jako v push
        TStackElement* new_values = malloc(aStack->iCapacity * sizeof(TStackElement));
        for (int i = 0; i < aStack->iCount; i++)
            new_values[i] = aStack->iValues[i];
        
        //aStack->iValues = NULL;
        //nebo                          // stejně, jako v push
        free(aStack->iValues);
        
        aStack->iValues = new_values;
        return true;
    }
}

void stack_destroy (struct TStack* aStack) {
    free(aStack->iValues);
    stack_init(aStack);
}

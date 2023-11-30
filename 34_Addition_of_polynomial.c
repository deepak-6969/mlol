#include <stdio.h>
#include <stdlib.h>

// Node structure for a term in the polynomial
struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

// Function to create a new term node
struct Node* createNode(int coefficient, int exponent) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into the polynomial
void insertTerm(struct Node** poly, int coefficient, int exponent) {
    struct Node* newNode = createNode(coefficient, exponent);

    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* current = *poly;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
    }
}

// Function to display a polynomial
void displayPolynomial(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coefficient, poly->exponent);

        if (poly->next != NULL) {
            printf(" + ");
        }

        poly = poly->next;
    }

    printf("\n");
}

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* current1 = poly1;
    struct Node* current2 = poly2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent > current2->exponent) {
            insertTerm(&result, current1->coefficient, current1->exponent);
            current1 = current1->next;
        } else if (current1->exponent < current2->exponent) {
            insertTerm(&result, current2->coefficient, current2->exponent);
            current2 = current2->next;
        } else {
            // Add coefficients when exponents are equal
            insertTerm(&result, current1->coefficient + current2->coefficient, current1->exponent);
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // Add remaining terms from poly1
    while (current1 != NULL) {
        insertTerm(&result, current1->coefficient, current1->exponent);
        current1 = current1->next;
    }

    // Add remaining terms from poly2
    while (current2 != NULL) {
        insertTerm(&result, current2->coefficient, current2->exponent);
        current2 = current2->next;
    }

    return result;
}

// Function to free memory allocated for a polynomial
void freePolynomial(struct Node* poly) {
    struct Node* current = poly;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    // Create and display first polynomial: 3x^2 + 2x + 5
    struct Node* poly1 = NULL;
    insertTerm(&poly1, 3, 2);
    insertTerm(&poly1, 2, 1);
    insertTerm(&poly1, 5, 0);
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    // Create and display second polynomial: 2x^3 + 4x + 1
    struct Node* poly2 = NULL;
    insertTerm(&poly2, 2, 3);
    insertTerm(&poly2, 4, 1);
    insertTerm(&poly2, 1, 0);
    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Add polynomials and display the result: 2x^3 + 3x^2 + 6x + 6
    struct Node* result = addPolynomials(poly1, poly2);
    printf("Resultant Polynomial: ");
    displayPolynomial(result);

    // Free memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(result);

    return 0;
}

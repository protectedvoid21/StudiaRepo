from typing import List, Tuple


def get_confusion_matrix(
    y_true: List[int], y_pred: List[int], num_classes: int,
) -> List[List[int]]:
    """
    Generate a confusion matrix in a form of a list of lists.

    :param y_true: a list of ground truth values
    :param y_pred: a list of prediction values
    :param num_classes: number of supported classes

    :return: confusion matrix
    """
    
    if len(y_true) != len(y_pred):
        raise ValueError("Invalid input shapes!")
    
    max_class = max([max(y_true), max(y_pred)]) + 1
    
    if max_class != num_classes:
        raise ValueError("Invalid prediction classes!")

    matrix = [[0 for _ in range(num_classes)] for _ in range(num_classes)]
        
    for i in range(len(y_true)):
        matrix[y_true[i]][y_pred[i]] += 1
                
                
    return matrix
                


def get_quality_factors(
    y_true: List[int],
    y_pred: List[int],
) -> Tuple[int, int, int, int]:
    """
    Calculate True Negative, False Positive, False Negative and True Positive 
    metrics basing on the ground truth and predicted lists.

    :param y_true: a list of ground truth values
    :param y_pred: a list of prediction values

    :return: a tuple of TN, FP, FN, TP
    """
    TN_count = FP_count = FN_count = TP_count = 0
    
    for i in range(len(y_true)):
        match (y_true[i], y_pred[i]):
            case 1, 1: TP_count += 1
            case 0, 0: TN_count += 1
            case 0, 1: FP_count += 1
            case 1, 0: FN_count += 1
        
    return TN_count, FP_count, FN_count, TP_count
        
    

def accuracy_score(y_true: List[int], y_pred: List[int]) -> float:
    """
    Calculate the accuracy for given lists.
    :param y_true: a list of ground truth values
    :param y_pred: a list of prediction values

    :return: accuracy score
    """
    correct_value_count = sum(1 for i in range(len(y_true)) if y_true[i] == y_pred[i])
    
    return correct_value_count / len(y_true)

def precision_score(y_true: List[int], y_pred: List[int]) -> float:
    """
    Calculate the precision for given lists.
    :param y_true: a list of ground truth values
    :param y_pred: a list of prediction values

    :return: precision score
    """
    true_positives_count = 0
    false_positives_count = 0

    for i in range(len(y_true)):
        if y_true[i] == y_pred[i] == 1:
            true_positives_count += 1

        if y_true[i] == 0 and y_pred[i] == 1:
            false_positives_count += 1

    if true_positives_count + false_positives_count == 0:
        return 0
    
    return true_positives_count / (true_positives_count + false_positives_count)


def recall_score(y_true: List[int], y_pred: List[int]) -> float:
    """
    Calculate the recall for given lists.
    :param y_true: a list of ground truth values
    :param y_pred: a list of prediction values

    :return: recall score
    """
    true_positives_count = 0
    false_negatives_count = 0

    for i in range(len(y_true)):
        if y_true[i] == y_pred[i] == 1:
            true_positives_count += 1

        if y_true[i] == 1 and y_pred[i] == 0:
            false_negatives_count += 1

    if true_positives_count + false_negatives_count == 0:
        return 0

    return true_positives_count / (true_positives_count + false_negatives_count)


def f1_score(y_true: List[int], y_pred: List[int]) -> float:
    """
    Calculate the F1-score for given lists.
    :param y_true: a list of ground truth values
    :param y_pred: a list of prediction values

    :return: F1-score
    """
    recall = recall_score(y_true, y_pred)
    precision = precision_score(y_true, y_pred)
    
    return 2 * precision * recall / (precision + recall)
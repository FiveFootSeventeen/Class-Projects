//Code adapted from instructor's example
function deleteTransaction(id){
    $.ajax({
        url: '/transaction/' + id,
        type: 'DELETE',
        success: function(result){
            window.location.reload(true);
        }
    })
};
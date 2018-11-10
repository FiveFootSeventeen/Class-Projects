//Code adapted from instructor's example
function deleteProduct(id){
    $.ajax({
        url: '/product/' + id,
        type: 'DELETE',
        success: function(result){
            window.location.reload(true);
        }
    })
};